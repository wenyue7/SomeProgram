#########################################################################
# File Name: lhjbackup.sh
# Author: LiHongjin
# mail: 872648180@qq.com
# Created Time: Tue Apr  5 15:27:21 2022
#########################################################################
#!/bin/bash

# crontab -e
# * 4 * * * sh ~/Projects/Some-program/lhjbackup.sh

usrHome="/Users/$(whoami)"

# src
srcDirPerLoc="$usrHome/Documents/doc"
srcDirPerNetRoot="$usrHome/Documents"
srcDirPerNet="doc"

srcDirWorkLoc="$usrHome/Documents/rk-doc"
srcDirWorkNetRoot="$usrHome/Documents/rk-doc"
srcDirWorkNet="2.工作资料 3.输出资料 4.总结汇报"

# dst
dstDirLoc="/Volumes/exdisk/document"
dstDirNet="$usrHome/Library/CloudStorage/OneDrive-Personal/文档"

echo "==> backup per dir to loc"
time cp -r $srcDirPerLoc $dstDirLoc 2> /dev/null
# cp -r $srcDirPerNet $dstDirNet
echo

echo "==> backup work dir to loc"
time cp -r $srcDirWorkLoc $dstDirLoc 2> /dev/null
echo

echo "==> backup per dir to net"
time tar -zcPvf $dstDirNet/perbackup$(date +%Y%m%d).tar.gz -C $srcDirPerNetRoot $srcDirPerNet 2> /dev/null
echo
echo "==> backup work dir to net"
time tar -zcPvf $dstDirNet/workbackup$(date +%Y%m%d).tar.gz -C $srcDirWorkNetRoot \
    --exclude="./2.工作资料/kernel编译/prebuilts" --exclude="./2.工作资料/kernel编译/prebuilts.zip" \
    --exclude="./2.工作资料/协议" \
    $srcDirWorkNet 2> /dev/null
echo

#删除文件夹下超过30天的文件
find $dstDirNet -mtime +30 -name "*.tar.gz" -exec rm -rf {} \;
