#一个简单的二分测试程序交互器
#把./test改成自己的程序名，如windows下改成test.exe，linux下同一目录需要加./或者用绝对路径
import subprocess
import random
s=subprocess.Popen("./test",stdout=subprocess.PIPE,stdin=subprocess.PIPE,stderr=subprocess.PIPE)
ans = random.randint(1,1000)
print("(debug)","ans=",ans)
for i in range(20):
	out = int(s.stdout.readline().decode("utf-8"))
	print("debug",out)
	outbuf = ""
	if out == ans:
		outbuf = str(0)
		print("Check Passed")
		break
	elif int(out) < ans:
		outbuf = str(-1)
	else:
		outbuf = str(1)
	outbuf += "\n"#换行非常重要，否则可能导致程序无法读入
	s.stdin.write(outbuf.encode("utf-8"))
	s.stdin.flush()
	print("(debug)","i=",i)
s.kill()