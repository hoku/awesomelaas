
# AwesomeLaaS

AwesomeLaaSとは、世界初かもしれない「LaaS（Lip as a Service）」を実現するためのソフトウェア。


# LaaS（Lip as a Service）とは？

LaaS（Lip as a Service）とは「サービスとしてのリップ」を意味し、リップをクラウドサービスとして提供する。  
知らんけど。


# 導入方法

```Shell
# ソースの取得
git clone https://github.com/hoku/awesomelaas.git

# ビルド
cd awesomelaas
gcc -o laas laas.c

# 実行
sudo nohup ./laas &
```


# 利用方法例

```Shell
curl http://your_laas_url
```

```PHP
<?php
$result = json_decode(file_get_contents("http://your_laas_url"));
$lip = $result->lip ?? '';
?>
<html>
<body>
    <strong><?= htmlspecialchars($lip) ?></strong>
</body>
</html>
```


# ライセンス

MIT License
