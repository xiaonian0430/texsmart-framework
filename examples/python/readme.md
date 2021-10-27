
========== Frequently Asked Questions (FAQs) ==========

Q1. I got the following messsage in running chs_nlu_example1.py with Python 2 on Linux:
	File "chs_nlu_example1.py", line 12, in <module>
		print(u'=== 解析一个中文句子 ===')
	UnicodeEncodeError: 'ascii' codec can't encode characters in position 4-11: ordinal not in range(128)
How to solve this?

Answer: This is probably because ANSI encoding is used by stdout in the print function to encode unicode strings.
	Solution-1: Set the PYTHONIOENCODING environment variable when running the example:
		PYTHONIOENCODING=UTF-8 python nlu_python_example1.py
	Solution-2: Set your global locale to en_US.utf8:
		Step-1: Open your bash shell profile file: vi ~/.bash_profile
		Step-2: Append/edit lines as follows:
			LANG="en_US.utf8"
			export LANG
		Step-3: Reload the shell profile: source ~/.bash_profile (or by logging out and back in again, of course)
		(Type the "locale" command to verify that your locale change has taken effect.)

Q2.  What can I do when the following error message is displayed?
	File ".\en_nlu_example1.py", line 7, in <module>
		from tencent_ai_texsmart import *
	ImportError: No module named tencent_ai_texsmart

Answer: You may have copied the script to another folder, without modifying line 6:
		sys.path.append(module_dir+'/../../lib/')
	Solution-1: Change the above line in the script to add the correct directory of tencent_ai_texsmart.py to sys.path.
	Solution-2: Config the PYTHONPATH environment variable to add the directory where tencent_ai_texsmart.py resides.
	File tencent_ai_texsmart.py is in ${texsmart_root}/lib/, where ${texsmart_root} is the root directory of texsmart.

Q3. How to remove the following error messages?
	Failed to load data spec
	Failed to initialize the NLU engine

Answer: You may have copied the script to another folder, without modifying line 10:
		engine = NluEngine(module_dir + '/../../data/nlu/kb/')
	Solution: Change the above line to set the correct data folder for the NLU engine.
		The data folder for the NLU engine is ${texsmart_root}/data/nlu/kb/, where ${texsmart_root} is the root directory of texsmart.
