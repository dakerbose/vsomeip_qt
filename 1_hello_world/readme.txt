1. client是在虚拟机上面配置的 192.168.123.52 ens33 虚拟机桥接 复制物理网络接口
   g++ -o client client.cpp -L/usr/local/lib -lvsomeip3
   VSOMEIP_CONFIGURATION=vsomeip_client.json ./client
   
   
2. service是在树莓派 wlan0上面配置的192.168.123.154
   g++ -std=c++11 server.cpp -o server -lvsomeip3 -pthread
   VSOMEIP_CONFIGURATION=vsomeip_server.json ./server
   
   
