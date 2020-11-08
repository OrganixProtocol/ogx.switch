# ogx.switch 介绍

ogx token pre sale contract

# ogx.presale编译部署

## 依赖环境

1. eosio.cdt --- tag: v1.7.0 或以上
2. eosio.contract --- tag:  v1.9.1 或以上

## 编译

#### 1. 将ogx.presale目录放入eosio.contracts内,跟eosio.token同级即可。
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
合约帐号: ogxprestoken
代币OGX合约帐号: organixtoken
代币EOS合约帐号: eosio.token
代币TPT合约帐号: eosiotptoken

```

## 部署
```
cd build
cleos -u 'https://eospush.tokenpocket.pro' system newaccount itokenpocket ogxfundation EOS77f1D5xApr9RaE7vS6ZDqWb9HteXhakoHgU6GZV6RzFu4tzTSR EOS77f1D5xApr9RaE7vS6ZDqWb9HteXhakoHgU6GZV6RzFu4tzTSR --buy-ram '1.0000 EOS' --stake-net '1.0000 EOS' --stake-cpu '0.0001 EOS'
cleos -u 'https://eospush.tokenpocket.pro' system newaccount itokenpocket ogxmarketing EOS77f1D5xApr9RaE7vS6ZDqWb9HteXhakoHgU6GZV6RzFu4tzTSR EOS77f1D5xApr9RaE7vS6ZDqWb9HteXhakoHgU6GZV6RzFu4tzTSR --buy-ram '1.0000 EOS' --stake-net '1.0000 EOS' --stake-cpu '0.0001 EOS'
cleos -u 'https://eospush.tokenpocket.pro' system newaccount itokenpocket ogxeosioteam EOS77f1D5xApr9RaE7vS6ZDqWb9HteXhakoHgU6GZV6RzFu4tzTSR EOS77f1D5xApr9RaE7vS6ZDqWb9HteXhakoHgU6GZV6RzFu4tzTSR --buy-ram '0.3000 EOS' --stake-net '1.0000 EOS' --stake-cpu '0.0001 EOS'
cleos -u 'https://eospush.tokenpocket.pro' system newaccount itokenpocket ogxprestoken EOS77f1D5xApr9RaE7vS6ZDqWb9HteXhakoHgU6GZV6RzFu4tzTSR EOS77f1D5xApr9RaE7vS6ZDqWb9HteXhakoHgU6GZV6RzFu4tzTSR --buy-ram '1.0000 EOS' --stake-net '1.0000 EOS' --stake-cpu '0.0001 EOS'
cleos -u 'https://eospush.tokenpocket.pro' set account permission ogxprestoken active '{"threshold": 1,"keys": [{"key": "EOS77f1D5xApr9RaE7vS6ZDqWb9HteXhakoHgU6GZV6RzFu4tzTSR", "weight": 1}],"accounts": [{"permission":{"actor":"ogxprestoken","permission":"eosio.code"},"weight":1}]}' owner -p ogxprestoken@owner
cleos -u 'https://eospush.tokenpocket.pro' set contract ogxprestoken ./ogx.switch -p ogxprestoken

//代币合约授权
cleos -u 'https://eospush.tokenpocket.pro' set account permission organixtoken active '{"threshold": 1,"keys": [{"key": "EOS77f1D5xApr9RaE7vS6ZDqWb9HteXhakoHgU6GZV6RzFu4tzTSR", "weight": 1}],"accounts": [{"permission":{"actor":"ogxprestoken","permission":"eosio.code"},"weight":1}]}' owner -p organixtoken@owner

```
## 配置初始数据
```
cleos -u 'https://eospush.tokenpocket.pro' push action ogxprestoken addpair '["organixtoken", "15000000.0000 OGX", "15000000.0000 OGX", "eosio.token", "0.0000 EOS"]' -p ogxprestoken
cleos -u 'https://eospush.tokenpocket.pro' push action ogxprestoken addpair '["organixtoken", "5000000.0000 OGX", "5000000.0000 OGX", "eosiotptoken", "0.0000 TPT"]' -p ogxprestoken

cleos -u 'https://eospush.tokenpocket.pro' push action ogxprestoken deletepair '["1"]' -p ogxprestoken

```

## 查询
```
cleos -u 'https://eospush.tokenpocket.pro' get table ogxprestoken ogxprestoken pair
cleos -u 'https://eospush.tokenpocket.pro' get table ogxprestoken ogxprestoken pairinfo

cleos -u 'https://eospush.tokenpocket.pro' get currency balance organixtoken ogxfundation OGX
```

## 参与presale
```
//给organixtoken预留2000w OGX
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["organixtoken", "ogxfundation", "79999999.9999 OGX", ""]' -p organixtoken
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "ogxmarketing", "6000000.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "ogxeosioteam", "25000000.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "ogxprivate11", "31484537.5006 OGX", ""]' -p ogxfundation

//参与
cleos -u 'https://eospush.tokenpocket.pro' push action eosio.token transfer '["tokenfletest", "ogxprestoken", "100.0000 EOS", ""]' -p tokenfletest
cleos -u 'https://eospush.tokenpocket.pro' push action eosiotptoken transfer '["tokenfletest", "ogxprestoken", "500000.0000 TPT", ""]' -p tokenfletest
```

## 清算
```
cleos -u 'https://eospush.tokenpocket.pro' push action ogxprestoken dist '["eosiotptoken", "4,TPT", "200"]' -p ogxprestoken
```

## 其他
```
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "gonglianyun1", "50.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "newdexsweety", "50.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "ruyi11111111", "50.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "newdexsweety", "20000.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "whaleairdrop", "21000.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "gonglianyun1", "12388.4784 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "candyboxoftp", "28357.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxmarketing", "ogxprivate11", "81895.4784 OGX", ""]' -p ogxmarketing
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxmarketing", "candyboxoftp", "39454.0000 OGX", ""]' -p ogxmarketing
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxmarketing", "ogxcommunity", "200000.0000 OGX", ""]' -p ogxmarketing

cleos -u 'https://eospush.tokenpocket.pro' push action eosiotptoken transfer '["ogxprestoken", "tpburningacc", "126326427.4996 TPT", ""]' -p ogxprestoken

//第一批1/4
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "dex.hi", "233212.5000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "pralinlin111", "116606.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "lijielijie54", "233212.5000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "seed.newdex", "69963.7500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eostaotao123", "216607.7700 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "55.game", "359895.8333 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eosrammoon31", "233212.5000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eos555gogogo", "284958.3229 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "youxiwang123", "216875.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "bingbang1234", "220575.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "djshsys2jdnj", "661725.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "mayunbaba123", "113618.7500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "gezdsnrqhege", "272685.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "torchesfrms5", "22723.7500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "55.game", "361458.5213 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eos123cpu123", "98840.6666 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "poiulkjhmnbc", "100306.9167 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "myeoszhiqian", "100306.9167 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "batcat123451", "100306.9167 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "guztaojsgage", "373870.9167 OGX", ""]' -p ogxfundation

cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "g43tmmbqgige", "326497.5000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "yangyangeosi", "46642.5000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "wuxiang12345", "2052.2700 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eos123cpu123", "93285.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "bihu55555555", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "wenyouqiyuan", "32369.9000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "bengangeos12", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "hlloveinglxe", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "ziyouzhilu12", "44543.5900 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "xiao12345124", "4664.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "luotiecheng3", "13992.7500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "freeskyofeos", "46642.5000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "yycomeonbaby", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "afujunzhi513", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "nvshennvshen", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "liyinlong.m", "18181.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "gq4tiojqgqge", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "onetaoeos123", "2332.1300 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eoszqxzqxzqx", "11660.6300 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "farlongsails", "27985.5000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eos555gogogo", "116606.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "cynthiacaoyi", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "farlongsails", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "ieosblochain", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eos555gogogo", "93285.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "fa5555555555", "46642.5000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "w5555555555w", "9328.5000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "victorwinwin", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "gq3dcnjuhage", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "g44tqojuguge", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "wsxoknqazplm", "46.6400 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "wsxoknqazplm", "23531.1400 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eosiowindows", "55971.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "w5u4b3o21.tp", "12290.3000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "linghunbaidu", "23437.8600 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "iost33333.tp", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "333eoseoseos", "11660.6300 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "gq2danzygene", "69963.7500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "zxcvbnm33222", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "xiaohangzhou", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eos123cpu123", "111942.0000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "richrichrich", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eos112233.tp", "58303.1300 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "yanghappnews", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "u.sb", "46642.5000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eostptaiwan1", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "haomingeospk", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eosmelo12345", "46642.5000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "gm2tqnrqhege", "23321.2500 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "qojmfb2iszyk", "43664.1700 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "shaojun11111", "21832.0800 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "summermajic1", "22050.4000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "freeskyofeos", "21832.0800 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "linkinfuture", "10916.0400 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "weifengjiang", "21832.0800 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "neilchenrich", "21832.0800 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eoslikechina", "21832.0800 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "4.com", "21832.0800 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eosqianjiang", "21832.0800 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "fengzichenba", "22057.5000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "dfs111111111", "198517.5000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eosofalibaba", "14395.8300 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "dcjhotmykey2", "14395.8300 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "gm4dkmjwhage", "10796.8800 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "eosbelievein", "24832.8100 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "bihanghai.tp", "224215.1000 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "stenzhou1234", "25998.8800 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "zhangqian222", "72291.6700 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "lucyandlilei", "15174.0200 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "zhangqian222", "144583.3300 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "zhangqian222", "144583.3300 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxfundation", "evanswu24.tp", "14416.6700 OGX", ""]' -p ogxfundation
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxprivate11", "sd5zp2ljyltp", "849414.5000 OGX", ""]' -p ogxprivate11
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxprivate11", "gonbodefi111", "1250000.0000 OGX", ""]' -p ogxprivate11

cleos -u 'https://eospush.tokenpocket.pro' push action tethertether transfer '["ogxprivate11", "djsja24djdjs", "28950.0000 USDT", ""]' -p ogxprivate11
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxmarketing", "3h2mqewpoka4", "100000.0000 OGX", ""]' -p ogxmarketing
cleos -u 'https://eospush.tokenpocket.pro' push action eosio.token transfer '["ogxprestoken", "ogxprivate11", "19900.0000 EOS", ""]' -p ogxprestoken

//退回剩余的tpt
cleos -u 'https://eospush.tokenpocket.pro' push action eosiotptoken transfer '["tpwallet1113", "myeoszhiqian", "185000000.0000 TPT", ""]' -p tpwallet1113
cleos -u 'https://eospush.tokenpocket.pro' push action eosiotptoken transfer '["tpwallet1113", "batcat123451", "119000000.0000 TPT", ""]' -p tpwallet1113
cleos -u 'https://eospush.tokenpocket.pro' push action eosiotptoken transfer '["tpwallet1113", "poiulkjhmnbc", "187862084.7551 TPT", ""]' -p tpwallet1113
cleos -u 'https://eospush.tokenpocket.pro' push action eosiotptoken transfer '["tpwallet1113", "quqlabfoalqj", "38778342.3648 TPT", ""]' -p tpwallet1113
cleos -u 'https://eospush.tokenpocket.pro' push action eosiotptoken transfer '["tpwallet1113", "qpajdnslansq", "25029013.9871 TPT", ""]' -p tpwallet1113
cleos -u 'https://eospush.tokenpocket.pro' push action eosiotptoken transfer '["tpwallet1113", "aboqnzmalaqp", "38672628.9717 TPT", ""]' -p tpwallet1113
//总量: 860341728
//0.2266541232
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxeosioteam", "zhour1234.tp", "132812.5000 OGX", ""]' -p ogxeosioteam
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxeosioteam", "myeoszhiqian", "359466.6232 OGX", ""]' -p ogxeosioteam
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxeosioteam", "batcat123451", "282752.9200 OGX", ""]' -p ogxeosioteam
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxeosioteam", "poiulkjhmnbc", "362793.3060 OGX", ""]' -p ogxeosioteam
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxeosioteam", "quqlabfoalqj", "45073.1851 OGX", ""]' -p ogxeosioteam
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxeosioteam", "qpajdnslansq", "29091.9435 OGX", ""]' -p ogxeosioteam
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxeosioteam", "aboqnzmalaqp", "44950.3107 OGX", ""]' -p ogxeosioteam
cleos -u 'https://eospush.tokenpocket.pro' push action organixtoken transfer '["ogxeosioteam", "hbecofund123", "743059.2115 OGX", ""]' -p ogxeosioteam

cleos -u 'https://eospush.tokenpocket.pro' push action eosiotptoken transfer '["tpburningacc", "eosiotptoken", "133047066.4996 TPT", ""]' -p tpburningacc

curl -H "Accept: application/json" -H "Content-type: application/json" -H "token: NDU3NGQzNzFlOTFhNmE4OTJlN2UwY2Y0Yzg0ODUxOGFkN2RlNzFjODBlNDNkMDE0YTc2MTNlNTJiM2UxZTliZjVlN2ExM2RmMTY4OGMxODI5YmMzMGE0ZTNjNmMwZTEzXjAyMGI3OWY0MTA0MzYzOTJkYmQxYTJkOWFkOWRmZGRi" -X POST -d '{"blockchain_id": 10, "timeout":180}'  http://172.31.233.104:8382/v1/admin/currency_token/collect_blockchain

```