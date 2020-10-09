#./test改成程序的名称
import subprocess
import random
s=subprocess.Popen("./test",stdout=subprocess.PIPE,stdin=subprocess.PIPE,stderr=subprocess.PIPE)
ans = random.randint(1,1000)
print("(debug)","ans=",ans)
for i in range(20):
	out = int(s.stdout.readline().decode("utf-8"))
	print("debug",out)
	if int(out) == ans:
		s.stdin.write(str(0).encode("utf-8"))
		break
	elif int(out) < ans:
		s.stdin.write(str(-1).encode("utf-8"))
	else:
		s.stdin.write(str(1).encode("utf-8"))
	s.stdin.write("\n".encode("utf-8"))
	s.stdin.flush()
	print("(debug)","i=",i)
s.kill()