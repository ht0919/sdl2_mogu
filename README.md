# モグラ叩き for macOS

- C言語とSDL2によるゲームのサンプルです。
- macOS High Sierra (10.13.6) で動作確認しています。
- mogu_main.c の DUMMYWAIT で全体のスピードを調整できます。


## SDL2のインストール(要Homebrew)

- $ brew install sdl2 sdl2_ttf sdl2_mixer


## ビルド方法

- $ make


## 実行方法

- $ ./mogu


## 不要ファイル(*.o,mogu)の削除

- $ make clean

