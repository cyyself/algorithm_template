#./test改成程序的名称
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
	outbuf += "\n"
	s.stdin.write(outbuf.encode("utf-8"))
	s.stdin.flush()
	print("(debug)","i=",i)
s.kill()