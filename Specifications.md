# 機能要求

## 行列形式のリスト表示
- テキストの文字の色を設定可能
- 背景色を奇数行と偶数行で別個に設定可能
- セルに表示しきれない部分がツールチップ表示される

## テキストのインデント表示
- 行ごとに同じインデント量であればよい
- 適用される列を任意に指定可能
- アイコンも併せてインデントされる

## 列のプロパティ設定
- 現在の列の数の取得が可能
- 列の追加削除および以下のプロパティの変更が可能
	- 列タイトル（列ヘッダ表示テキスト）
	- 表示位置（左揃え・中央揃え・右揃え）
	- インデント適用有無

## 列ヘッダ表示
- 列ヘッダ表示有無の指定可能
- 文字色を任意に設定可能
- 背景色を任意に設定可能

## 任意のフォント設定

## スクロールバー表示
- コントロールの大きさに表示しきれない場合はスクロールバーを表示
- 現在のスクロールバー表示有無とスクロール位置を取得可能
- 現在表示されているうち先頭の行を取得可能
- 任意の行、列、またはセルが表示されるようにスクロール可能
- 最初の任意の数の行または列をスクロールさせず固定表示が可能
- 列幅の自動調整により縦スクロールバーを表示しない設定が可能

## 各セルにアイコン表示
- テキストがある場合は左端に表示
- テキストがない場合には左端または中央に表示（列のテキスト表示位置に依存）

## 表示情報（セルのテキスト、インデント、アイコン）の取得方法
- 現在の行数の取得が可能
- 表示情報の決定方法を以下の形式で選択可能
	- コントロール自身が内部で保持
		- セルのテキスト、インデント、アイコン情報を取得可能
	- 以下のいずれかの外部オブジェクトから表示時に取得（どれでも可能）
		- 親ウィンドウ
		- コントロールクラスの派生クラス
		- 外部データソースオブジェクト

## 項目選択
- 選択の単位は行、列、セルのいずれかを任意で設定可能
- 選択可能な項目数は最大1個でよい（複数選択は必要ない）
- 現在の選択項目の文字色および背景色はシステムカラーでよい

## 入力フォーカス時のユーザ入力検出
- マウス入力イベントを外部オブジェクトに通知
- 座標情報から項目の行および列を識別可能
- 座標情報から項目の部位（アイコン、テキスト、その他）を識別可能

## ユーザによるセルへの直接入力
- 入力開始は外部からの指定時のみでよい（クリック等で自動で開始する必要はない）
- 確定（Enter押下やフォーカスアウト）、キャンセル（ESC押下）を外部オブジェクトに通知
