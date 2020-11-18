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
代币老OGX合约帐号: ogxtokentok1
代币OGX合约帐号: organixtokep

```

## 部署
```
//领取测试网络的EOS
curl http://faucet-kylin.blockzone.net/get_token/itokenpocket

cd build
cleos -u 'http://api.kylin.alohaeos.com' system newaccount itokenpocket ogxswitch111 EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py --buy-ram '20.0000 EOS' --stake-net '1.0000 EOS' --stake-cpu '10.0000 EOS'
cleos -u 'http://api.kylin.alohaeos.com' set account permission ogxswitch111 active '{"threshold": 1,"keys": [{"key": "EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py", "weight": 1}],"accounts": [{"permission":{"actor":"ogxswitch111","permission":"eosio.code"},"weight":1}]}' owner -p ogxswitch111@owner
cleos -u 'http://api.kylin.alohaeos.com' set contract ogxswitch111 ./ogx.switch -p ogxswitch111

//老代币合约
cleos -u 'http://api.kylin.alohaeos.com' system newaccount itokenpocket ogxtokentok1 EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py --buy-ram '20.0000 EOS' --stake-net '1.0000 EOS' --stake-cpu '10.0000 EOS'
cleos -u 'http://api.kylin.alohaeos.com' set contract ogxtokentok1 ./eosio.token -p ogxtokentok1
cleos -u 'http://api.kylin.alohaeos.com' push action ogxtokentok1 create '["ogxtokentok1", "100000000.0000 OGX"]' -p ogxtokentok1
cleos -u 'http://api.kylin.alohaeos.com' push action ogxtokentok1 issue '["ogxtokentok1", "100000000.0000 OGX", ""]' -p ogxtokentok1

```
## 查询
```
cleos -u 'http://api.kylin.alohaeos.com' get currency balance organixtoke1 tokenfletest OGX
```

## 参与switch
```
//获取老的token
cleos -u 'http://api.kylin.alohaeos.com' push action ogxtokentok1 transfer '["ogxtokentok1", "organixttest", "30000.0000 OGX", ""]' -p organixttest

//兑换新的token
cleos -u 'http://api.kylin.alohaeos.com' push action ogxtokentok1 transfer '["organixttest", "ogxswitch111", "30000.0000 OGX", ""]' -p organixttest

```