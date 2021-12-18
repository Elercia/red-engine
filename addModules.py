import glob
import os

cppFiles = glob.glob("engine/src/**/**.cpp", recursive=True)

for filename in cppFiles:
	
	fullFileName = os.path.join("/mnt/a/Documents/engines/red-engine/", filename);
	print("Opening ", fullFileName)

	file = open(fullFileName, mode='r+', encoding='utf-8')
	filecontent = file.read()

	if not filecontent:
		print("empty file")

	dirs = filename.split("/")

	moduleName = dirs[2] # [engine src <moduleName>]

	includeStr = '#include "RedEngine/{module_name}/{module_name}Module.hpp"'.format(module_name=moduleName)

	print(filename, " : ", includeStr)
	print(filecontent)

	#new_file_content = "{include}\n{rest}".format(rest=contents[1], include=includeStr)

	# file.write(new_file_content)

	file.close()