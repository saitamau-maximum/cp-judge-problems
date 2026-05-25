# Judge Problems

このリポジトリは、 Maximum でホストしている DOMjudge にある問題を管理するためのものです。

ICPC などの問題については、公式サイト (<https://icpc.jp> など) からダウンロードしたデータを展開し用いています。
詳しくは、各コンテストディレクトリの README.md に記載があります。

## ディレクトリ構造

```plaintext
[contest-name]/
├── contest.yaml
├── Makefile
└── [problem-name]/
    ├── domjudge-problem.ini
    ├── problem.{pdf,html,txt}
    ├── problem.yaml
    ├── data/
    │   ├── sample/
    │   │   ├── [input].in
    │   │   └── [output].ans
    │   └── secret/
    │       ├── [input].in
    │       └── [output].ans
    └── output_validators/
        ├── run
        ├── build
        └── ...
```

`contest.yaml` および各問題のディレクトリの構造は、 DOMjudge のインポート形式に従います。
詳しくは [DOMjudge のドキュメント](https://www.domjudge.org/docs/manual/9.0/import.html) を参照してください。

`make icpc2025-prelim-a.zip` など、 Makefile で各問題の zip ファイルが生成できます。

## 免責事項

このリポジトリに含まれる問題のデータは、一部を除き各コンテストの公式サイトからダウンロードしたデータを使用しており、著作権は各コンテストの主催者に帰属します。
このリポジトリを使用したことによるいかなる損害についても、 Maximum は一切責任を負いません。
