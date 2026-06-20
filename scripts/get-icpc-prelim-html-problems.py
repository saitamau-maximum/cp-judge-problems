from pathlib import Path
from urllib.parse import urljoin
import re
import base64
import requests
from bs4 import BeautifulSoup
import htmlmin
import rcssmin


def stripped_search(pattern):
    def search(text):
        stripped_text = text.strip()
        return stripped_text == pattern

    return search


def inline_css(soup, problem_url):
    """
    HTML soup object から link タグで指定された CSS を取得し、style タグに置き換える
    """
    for link in soup.find_all("link", rel=re.compile(r"^stylesheet$", re.IGNORECASE)):
        href = link.get("href")
        if href:
            print(f"  {href}")
            css_url = urljoin(problem_url, href)
            css_resp = requests.get(css_url)
            css = css_resp.text
            style_tag = soup.new_tag("style")
            style_tag.string = css
            link.replace_with(style_tag)


def inline_image(soup, problem_url):
    """
    HTML soup object から img タグで指定された画像を取得し、base64 に変換して src 属性に埋め込む
    """
    for img in soup.find_all("img"):
        src = img.get("src")
        if src:
            print(f"  {src}")
            img_url = urljoin(problem_url, src)
            img_resp = requests.get(img_url)
            if src.endswith(".svg"):
                img_data = img_resp.text
                img_base64 = base64.b64encode(img_data.encode("utf-8")).decode("utf-8")
                img["src"] = f"data:image/svg+xml;base64,{img_base64}"
            else:
                img_data = img_resp.content
                img_base64 = base64.b64encode(img_data).decode("utf-8")
                img["src"] = f"data:image/png;base64,{img_base64}"


def get_problems_list(soup):
    """
    HTML soup object から問題一覧を取得する
    ICPC 2024 Prelim と同じ形式を想定
    """
    problems = []
    for a in (
        soup.find("td", class_="main")
        .find("h2", string=stripped_search("Links"))
        .find_next("div")
        .find_all("a")
    ):
        problems.append(a.text.strip())
    return problems


def minify_html(soup):
    """
    HTML soup object を minify し、結果の HTML を返す
    """
    for style in soup.find_all("style"):
        if style.string:
            minified_css = rcssmin.cssmin(style.string)
            style.string.replace_with(minified_css)
    minified_html = htmlmin.minify(
        str(soup),
        remove_comments=True,
        remove_empty_space=True,
        remove_optional_attribute_quotes=True,
    )
    return minified_html


def main():
    url = input("Problem HTML URL: ")
    resp = requests.get(url)
    resp.encoding = resp.apparent_encoding
    soup = BeautifulSoup(resp.text, "html5lib")
    soup = BeautifulSoup(soup.prettify(), "html.parser")

    # https://storage.googleapis.com/files.icpc.jp/domestic2024/contest/all_ja.html の形式を想定
    contest_slug = url.split("/")[-3]
    workdir = Path(contest_slug)
    workdir.mkdir(exist_ok=True)
    print(f"Workdir: {workdir.resolve()}")

    print("Inlining CSS...")
    inline_css(soup, url)

    print("Inlining images...")
    inline_image(soup, url)

    print("Getting problems list...")
    problems = get_problems_list(soup)
    print(f"  {problems}")

    # Links を削除
    soup.find("td", class_="main").find(
        "h2", string=stripped_search("Links")
    ).find_next("div").decompose()
    soup.find("td", class_="main").find(
        "h2", string=stripped_search("Links")
    ).decompose()

    print("Minifying HTML...")
    minified_html = minify_html(soup)

    print("Generating files...")
    for problem in problems:
        print(f"  Problem {problem}...")
        problem_soup = BeautifulSoup(minified_html, "html.parser")
        # ほかの問題を削除
        for a in problem_soup.find("td", class_="main").find_all("a"):
            if a.attrs is not None and a.get("name") != f"section_{problem}":
                a.decompose()
        # 空の div[align=right] を削除
        for div in problem_soup.find_all("div", align="right"):
            if not div.text.strip():
                div.decompose()
        # タイトルを変更
        problem_soup.find("title").string = f"Problem {problem}"

        with open(workdir / f"{problem}.html", "w", encoding="utf-8") as f:
            f.write(str(problem_soup))

    print("Done!")


if __name__ == "__main__":
    main()
