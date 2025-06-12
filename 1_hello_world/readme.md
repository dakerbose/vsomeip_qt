## 如果要测试双linux通讯

请回退到 a053c8fb80724a201793302b1218858b4f5bb3dc 
```
git reset a053c8fb80724a2
```
同一个网段ip自己配置
1. client是在虚拟机上面配置的 192.168.123.52 ens33 虚拟机桥接 复制物理网络接口
```
   g++ -o client client.cpp -L/usr/local/lib -lvsomeip3
   VSOMEIP_CONFIGURATION=vsomeip_client.json ./client
```
   
   
2. service是在树莓派 wlan0上面配置的192.168.123.154
```
   g++ -std=c++11 server.cpp -o server -lvsomeip3 -pthread
   VSOMEIP_CONFIGURATION=vsomeip_server.json ./server
```
## 如果要测试linux、QNX通讯
请回到 9b186126cf274a
```
   g++ -o client client.cpp -L/usr/local/lib -lvsomeip3
   VSOMEIP_CONFIGURATION=vsomeip_server.json ./server | grep -v "multicast"
```

在qnx中的这个子仓 中回退到 ccd054f52219ac
```
   ssh root@10.100.5.63
   cd /tmp 
   export LD_LIBRARY_PATH=/data/home/qnxuser/lib:/data/home/qnxuser/bin/vsomeip_tests/test/common:$LD_LIBRARY_PATH
   VSOMEIP_CONFIGURATION=vsomeip_client.json ./vsomeip_ecu
```
