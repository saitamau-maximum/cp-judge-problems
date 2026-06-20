# scripts

各種スクリプト置き場です

## get-icpc-prelim-html-problems.py

ICPC Prelim の問題文 (all) が HTML ファイルである場合 (~ 2024) に使えます。
HTML を解析し、問題文ごとに DOMjudge にインポート可能な HTML ファイルを生成します。

具体的には、以下の処理が行われます。

- CSS ファイルの inline 化
- 画像ファイルの inline 化
- minify
- 各問題のみが記述された HTML ファイルの出力 (`A.html`, `B.html` ... に出力されます)

```bash
# 依存関係のインストール
pip install requests beautifulsoup4 html5lib htmlmin rcssmin

# 実行
python3 get-icpc-prelim-html-problems.py
```

problem_all_ja の URL を入力すれば自動で進むはずです。
実行例:

```bash
$ python3 get-icpc-prelim-html-problems.py
Problem HTML URL: https://storage.googleapis.com/files.icpc.jp/domestic2024/contest/all_ja.html
Inlining CSS...
  ../common/icpc.css
Inlining images...
  ../common/images/icpc_logo.png
  figures/A1.jpg
  figures/B1.png
  figures/figC1.png
  figures/D1.png
  figures/D2.png
  figures/E1.png
  figures/E2.png
  figures/F1.png
  figures/F2.png
Getting problems list...
  ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I']
Minifying HTML...
Generating files...
  Problem A...
  Problem B...
  Problem C...
  Problem D...
  Problem E...
  Problem F...
  Problem G...
  Problem H...
  Problem I...
Done!
```
