#!/usr/bin/env python3
#用于打表时压缩数据
#Usage：
#1. 将打表的答案每行一个十进制数字输出到文件，例如文件名为1.txt
#2. 执行该文件，比如文件名为comp.py，执行python3 comp.py < 1.txt > biao.py
#为了更好压缩效果，可尝试将gzip改为bz2
import base64
import gzip
a = bytearray()
while True:
	try:
		x = int(input())
		a.append((x>>24) & 0xff)
		a.append((x>>16) & 0xff)
		a.append((x>>8) & 0xff)
		a.append((x>>0) & 0xff)
	except:
		break
zip_result = gzip.compress(a)
print("import base64\nimport gzip\ntmp = gzip.decompress(base64.b64decode({}))\narr = []\nfor i in range(len(tmp)//4):\n\tarr.append((tmp[i*4]<<24)|(tmp[i*4+1]<<16)|(tmp[i*4+2]<<8)|tmp[i*4+3])".format(base64.b64encode(zip_result)))
