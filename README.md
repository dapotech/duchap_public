# hapstack_m5atomS3_demo
詳しくはnotion
https://www.notion.so/hapstak-1e5fd544455e808f994bfa2f52587f70?pvs=4

## 環境
* ArduinoIDE2.0
* hapstakモジュール
* M5SAtomS3
* そこらへんに落ちてたアンプ
* アンプ用12Vアダプタ
ビルドが遅いのでPlatformIOに移行したくなっている

ミネベアの振動モーターに置換しても特に問題なく動いた

## 機能
* 画面裏のボタンでサンプル遷移
* 一定以上の加速度でサンプル動作
個人的にはマシンガンとかソードあたりがわかりやすい

## 参考
https://github.com/bit-trade-one/ADACHACY-hapStak
本家が出しているリポジトリ
M5Matrixで動作して要るっぽく苑麻安打と互換性がなかったので書き換えた

## 注意点
* アンプの出力上げすぎるとスピーカーが悲鳴をあげるので注意
* AtomS3のが目ぬらにボタンがあるのに気づくのに時間がかかった