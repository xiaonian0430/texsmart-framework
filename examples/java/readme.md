
Minimum Java version required: 1.6.0

========== Run the examples from a command line ==========
Take EnNluExample1.java as an example.

On Linux:
	Step-1: Compile
		javac -encoding utf8 -d bin -cp "../../lib/*" src/EnNluExample1.java
	Step-2: Run
		java -D"file.encoding"=utf8 -cp "bin:../../lib:../../lib/*" EnNluExample1

On Windows:
	Step-1: Compile
		javac -encoding utf8 -d bin -cp "../../lib/*" src/EnNluExample1.java
	Step-2: Run
		java -D"file.encoding"=utf8 -cp "bin;../../lib;../../lib/*" EnNluExample1
		
Comments:
	1) The commands on Linux and Windows are very similar. The only difference is the path separators (':' on Linux and ';' on Windows).
	2) For step-1, an alternative command is:
			javac -encoding utf8 -d bin -cp "../../lib/tencent.ai.texsmart.jar" src/NluExample1.java
	3) For step-2, an alternative command is:
		On Linux:
			java -D"file.encoding"=utf8 -cp "bin:../../lib:../../lib/tencent.ai.texsmart.jar:../../lib/jna.jar" NluExample1
		On Windows:
			java -D"file.encoding"=utf8 -cp "bin;../../lib;../../lib/tencent.ai.texsmart.jar;../../lib/jna.jar" NluExample1
	4) The "file.encoding" option in step-2 can often be removed in some environments. If so, the command will be simplified to:
			java -cp "bin;../../lib/*" NluExample1

========== Run the examples from an IDE ==========

Use an IDE (like Eclipse, IntelliJ IDEA, or NetBeans):
	1) Please make sure that the two jar files are added as external jars: tencent.ai.texsmart.jar, jna.jar
	2) Please set the data dir of the NLU engine properly in calling NluEngine.init().

========== Frequently Asked Questions (FAQs) ==========

Q1. I got the following messsage in running example 1:
	package tencent.ai.texsmart does not exist
How to solve this?

Answer: Possible reasons:
	1) Jar file tencent.ai.texsmart.jar is not specified in the javac or java command.
	2) The path of tencent.ai.texsmart.jar (in the value of the "-cp" option) is incorrect
	So the solution is to correctly set the path of tencent.ai.texsmart.jar and jna.jar.

Q2. How to handle the following error?
	Exception in thread "main" java.lang.UnsatisfiedLinkError: Unable to load library 'tencent_ai_texsmart':
	libtencent_ai_texsmart.so: cannot open shared object file: No such file or directory

Answer: Such kind of error occures when tencent.ai.texsmart.jar fails to load shared library libtencent_ai_texsmart.so (or tencent_ai_texsmart.dll on Windows).
	Solution: Check the -cp value string of the "java" command, to make sure that ${texsmart_root}/lib is listed.
	Here ${texsmart_root} is is the root directory of texsmart.
