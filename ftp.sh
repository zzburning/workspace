PROTO=ftp
USER=testuser                                用户名
PASSWD=testuserpwd                     密码
SERVER=NASERVER                     服务器
PORT=21                                        端口号
RDIR=/testuser                                私有资源路径；如使用fftp登录，公共资源路径为/incoming, /pub
CROSS_PKG_FILENAME=hxS2506a.K3_S2500_16SD.conf                        需下载的文件
URL="${PROTO}://${USER}:${PASSWD}@${SERVER}:${PORT}${RDIR}/${CROSS_PKG_FILENAME}"                 ftp完整的url
#get the cross package from our FTP server
if [ ! -f ${CROSS_PKG_FILENAME} ]; then
        echo "try download from FTP";
        if wget ${URL} 
        then
                echo "download ${CROSS_PKG_FILENAME} success."
        #exit ;
        else
                echo "downlaod ${CROSS_PKG_FILENAME} fail."
        exit ;
        fi
fi 
