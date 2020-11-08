# ogx.presale 介绍

ogx token pre sale contract

# ogx.presale编译部署

## 依赖环境

1. eosio.cdt --- tag: v1.7.0 或以上
2. eosio.contract --- tag:  v1.9.1 或以上

## 编译

#### 1. 将ogx.presale目录放入eosio.contracts内,跟eosio.token同级即可。
#### 2. 编辑文件 eosio.contracts/CMakeLists.txt:

```
add_subdirectory(ogx.presale)
```
#### 3. 运行eosio.contracts/build.sh完成编译
 ```
 ./build.sh
 ```
 
## 方案
```
合约帐号: ogxpresale11
代币OGX合约帐号: orgainxtoken
代币EOS合约帐号: orgainxtoke1
代币TPT合约帐号: orgainxtoke2

```

## 部署
```
//领取测试网络的EOS
curl http://faucet-kylin.blockzone.net/get_token/itokenpocket

cd build
cleos -u 'http://api.kylin.alohaeos.com' system newaccount itokenpocket ogxpresale11 EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8 --buy-ram '20.0000 EOS' --stake-net '1.0000 EOS' --stake-cpu '10.0000 EOS'
cleos -u 'http://api.kylin.alohaeos.com' set account permission ogxpresale11 active '{"threshold": 1,"keys": [{"key": "EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8", "weight": 1}],"accounts": [{"permission":{"actor":"ogxpresale11","permission":"eosio.code"},"weight":1}]}' owner -p ogxpresale11@owner
cleos -u 'http://api.kylin.alohaeos.com' set contract ogxpresale11 ./ogx.presale -p ogxpresale11

//代币合约授权
cleos -u 'http://api.kylin.alohaeos.com' system newaccount itokenpocket orgainxtoken EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8 --buy-ram '20.0000 EOS' --stake-net '1.0000 EOS' --stake-cpu '10.0000 EOS'
cleos -u 'http://api.kylin.alohaeos.com' set account permission orgainxtoken active '{"threshold": 1,"keys": [{"key": "EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8", "weight": 1}],"accounts": [{"permission":{"actor":"ogxpresale11","permission":"eosio.code"},"weight":1}]}' owner -p orgainxtoken@owner
cleos -u 'http://api.kylin.alohaeos.com' set contract orgainxtoken ./ogx.token -p orgainxtoken
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoken create '["orgainxtoken", "100000000.0000 OGX"]' -p orgainxtoken
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoken issue '["orgainxtoken", "100000000.0000 OGX", ""]' -p orgainxtoken


//代币合约授权
cleos -u 'http://api.kylin.alohaeos.com' system newaccount itokenpocket orgainxtoke1 EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8 --buy-ram '20.0000 EOS' --stake-net '1.0000 EOS' --stake-cpu '10.0000 EOS'
cleos -u 'http://api.kylin.alohaeos.com' set account permission orgainxtoke1 active '{"threshold": 1,"keys": [{"key": "EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8", "weight": 1}],"accounts": [{"permission":{"actor":"orgainxtoke1","permission":"eosio.code"},"weight":1}]}' owner -p orgainxtoke1@owner
cleos -u 'http://api.kylin.alohaeos.com' set contract orgainxtoke1 ./eosio.token -p orgainxtoke1
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke1 create '["orgainxtoke1", "1000000000.0000 EOS"]' -p orgainxtoke1
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke1 issue '["orgainxtoke1", "1000000000.0000 EOS", ""]' -p orgainxtoke1

cleos -u 'http://api.kylin.alohaeos.com' system newaccount itokenpocket orgainxtoke2 EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8 --buy-ram '20.0000 EOS' --stake-net '1.0000 EOS' --stake-cpu '10.0000 EOS'
cleos -u 'http://api.kylin.alohaeos.com' set account permission orgainxtoke2 active '{"threshold": 1,"keys": [{"key": "EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8", "weight": 1}],"accounts": [{"permission":{"actor":"orgainxtoke2","permission":"eosio.code"},"weight":1}]}' owner -p orgainxtoke2@owner
cleos -u 'http://api.kylin.alohaeos.com' set contract orgainxtoke2 ./eosio.token -p orgainxtoke2
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke2 create '["orgainxtoke2", "10000000000.0000 TPT"]' -p orgainxtoke2
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke2 issue '["orgainxtoke2", "10000000000.0000 TPT", ""]' -p orgainxtoke2

```
## 配置初始数据
```
cleos -u 'http://api.kylin.alohaeos.com' push action ogxpresale11 addpair '["orgainxtoke1", "15000000.0000 OGX", "15000000.0000 OGX", "orgainxtoke1", "0.0000 EOS"]' -p ogxpresale11
cleos -u 'http://api.kylin.alohaeos.com' push action ogxpresale11 addpair '["orgainxtoke1", "5000000.0000 OGX", "5000000.0000 OGX", "orgainxtoke2", "0.0000 TPT"]' -p ogxpresale11

cleos -u 'http://api.kylin.alohaeos.com' push action ogxpresale11 deletepair '["1"]' -p ogxpresale11

cleos -u 'http://api.kylin.alohaeos.com' push action ogxpresale11 clearpinfo '["100"]' -p ogxpresale11

```

## 查询
```
cleos -u 'http://api.kylin.alohaeos.com' get table ogxpresale11 ogxpresale11 pair
cleos -u 'http://api.kylin.alohaeos.com' get table ogxpresale11 ogxpresale11 pairinfo

cleos -u 'http://api.kylin.alohaeos.com' get currency balance orgainxtoken tokenfletest OGX
```

## 参与presale
```
//准备
//给orgainxtoken预留2000w OGX
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoken transfer '["orgainxtoken", "tokenfletest", "80000000.0000 OGX", ""]' -p orgainxtoken

//
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoken transfer '["tokenfletest", "orgainxtoken", "85106242.0000 OGX", ""]' -p tokenfletest
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoken transfer '["tokenfletes1", "orgainxtoken", "9893758.0000 OGX", ""]' -p tokenfletes1

//准备EOS, TPT
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke1 transfer '["orgainxtoke1", "tokenfletest", "40000000.0000 EOS", ""]' -p orgainxtoke1
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke1 transfer '["orgainxtoke1", "tokenfletes1", "40000000.0000 EOS", ""]' -p orgainxtoke1
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke1 transfer '["orgainxtoke1", "kylinclement", "40000000.0000 EOS", ""]' -p orgainxtoke1

cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke2 transfer '["orgainxtoke2", "tokenfletest", "100000000.0000 TPT", ""]' -p orgainxtoke2
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke2 transfer '["orgainxtoke2", "tokenfletes1", "300000000.0000 TPT", ""]' -p orgainxtoke2
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke2 transfer '["orgainxtoke2", "kylinclement", "3000000.0000 TPT", ""]' -p orgainxtoke2

//参与
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke1 transfer '["tokenfletest", "ogxpresale11", "100.0000 EOS", ""]' -p tokenfletest
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke1 transfer '["tokenfletest", "ogxpresale11", "1000.0000 EOS", "deposit:1"]' -p tokenfletest
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke1 transfer '["tokenfletest", "ogxpresale11", "4000.0000 EOS", "deposit:1"]' -p tokenfletest
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke1 transfer '["tokenfletest", "ogxpresale11", "5000.0000 EOS", "deposit:1"]' -p tokenfletest
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke1 transfer '["tokenfletes1", "ogxpresale11", "5000.0000 EOS", "deposit:1"]' -p tokenfletes1
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke1 transfer '["tokenfletes1", "ogxpresale11", "10000.0000 EOS", "deposit:1"]' -p tokenfletes1
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke1 transfer '["tokenfletes1", "ogxpresale11", "100000.0000 EOS", "deposit:1"]' -p tokenfletes1
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke2 transfer '["orgainxtoke2", "ogxpresale11", "300000.0000 EOS", ""]' -p orgainxtoke2

cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke2 transfer '["tokenfletest", "ogxpresale11", "40000.0000 TPT", ""]' -p tokenfletest
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke2 transfer '["tokenfletes1", "ogxpresale11", "5000000.0000 TPT", "1"]' -p tokenfletes1
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke2 transfer '["tokenfletes1", "ogxpresale11", "5100000.0000 TPT", "1"]' -p tokenfletes1
cleos -u 'http://api.kylin.alohaeos.com' push action orgainxtoke2 transfer '["orgainxtoke2", "ogxpresale11", "310000000.0000 TPT", ""]' -p orgainxtoke2

```

## 清算
```

cleos -u 'http://api.kylin.alohaeos.com' push action ogxpresale11 dist '["orgainxtoke2", "4,TPT", "30"]' -p ogxpresale11
cleos -u 'https://kylin.eos.dfuse.io' push action ogxpresale11 dist '["orgainxtoke2", "4,TPT", "30"]' -p ogxpresale11

```