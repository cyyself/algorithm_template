#!/usr/bin/env python3
header = "# CYY's Algorithm Template"
toc = ""
buf = ""
import os
suffix = ['cpp']
curpath = ''
for root,dirs,files in os.walk('.'):
	for file in files:
		if '/.' in root:
			continue
		if curpath != root:
			buf += '\n# ' + root + "\n"
			curpath = root
			toc += '- ' + root + "\n"
		filename = os.path.join(root,file)
		for x in suffix:
			if file.endswith('.'+x):
				toc += "\t- " + file + "\n"
				buf += "\n## " + file + "\n```" + x + "\n"
				print(file)
				with open(filename, 'r') as f:
					buf += f.read()
				buf += '```\n'
with open('output.md','w') as f:
	f.write(header + "\n" + toc + "\n" + buf)