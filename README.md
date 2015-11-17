Tamago
====
囲碁プログラムもどきです．改良中でバグだらけです． 
現在は人対人用のプログラムですが，最終的には対人プログラムにする予定です．

## Description
tamago3.cが本体です．

## Bug
* TakeStoneが再帰できていない（石が一つの場合は問題ないが2つ以上には無反応）
* prisoner（アゲハマ）がある時点で初期化される
* 入力として全角の文字を受けると再入力ではなくプログラムが終了する
* その他いろいろ

## Usage
x -> (Input from 1 to 19)

y -> (Input from 1 to 19)

Program end when Program is inpted 0 or string.

## Licence
Copyright (c) 2015 Mori

Released under the MIT license

http://opensource.org/licenses/mit-license.php

## Author
moritama1515
