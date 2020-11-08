# ogx.switch 介绍

ogx token switch contract

# ogx.switch编译部署

## 依赖环境

1. eosio.cdt --- tag: v1.7.0 或以上
2. eosio.contract --- tag:  v1.9.1 或以上

## 编译

#### 1. 将ogx.switch目录放入eosio.contracts内,跟eosio.token同级即可。
#### 2. 编辑文件 eosio.contracts/CMakeLists.txt:

```
add_subdirectory(ogx.switch)
```
#### 3. 运行eosio.contracts/build.sh完成编译
 ```
 ./build.sh
 ```
 
## 方案
```
合约帐号: ogxswitch111
代币老OGX合约帐号: organixtoken
代币OGX合约帐号: ogx

```

## 部署
```
cd build
cleos -u 'https://eospush.tokenpocket.pro' system newaccount itokenpocket ogxswitch111 EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8 --buy-ram '20.0000 EOS' --stake-net '1.0000 EOS' --stake-cpu '10.0000 EOS'
cleos -u 'https://eospush.tokenpocket.pro' set account permission ogxswitch111 active '{"threshold": 1,"keys": [{"key": "EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8", "weight": 1}],"accounts": [{"permission":{"actor":"ogxswitch111","permission":"eosio.code"},"weight":1}]}' owner -p ogxswitch111@owner
cleos -u 'https://eospush.tokenpocket.pro' set contract ogxswitch111 ./ogx.switch -p ogxswitch111

//新代币合约授权
cleos -u 'https://eospush.tokenpocket.pro' set account permission ogx active '{"threshold": 1,"keys": [{"key": "EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8", "weight": 1}],"accounts": [{"permission":{"actor":"ogxswitch111","permission":"eosio.code"},"weight":1}]}' owner -p ogx@owner

```
## 查询
```
cleos -u 'https://eospush.tokenpocket.pro' get currency balance organixtoke1 tokenfletest OGX
```

## 参与switch
```
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["organixttest", "organixtoken", "30000.0000 OGX", ""]' -p organixttest

```
