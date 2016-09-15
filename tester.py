from subprocess import Popen, PIPE, STDOUT
from random import randint

# ===================================================
# THESE ARE CRITICAL TO CHANGE !!!!
# ===================================================
MY_PROGRAM_NAME='./ConvexHull' # put the path to your solution exe here
SKOOL_PROGRAM_NAME = './SchoolSol' # put the path to skool_sol exe here
#===================================================


# some more vars to change
RANGE = (-2000,2000) # range of points
BASIC_TEST_INPUT="1,1\n2,2\n1,3\n4,5\n" # basic case
HARD_CASE_1="1,1\n2,2\n3,3\n" # hard cases
HARD_CASE_2="1,1\n2,2\n3,3\n1,3\n"
HARD_CASE_3="1,1\n2,2\n3,3\n3,1\n"
VERY_VERBOSE = False # how much printing shold be done

def open_program_with_input(prog,input_binary_string):

	proc = Popen([prog], stdout=PIPE, stdin=PIPE, stderr=STDOUT)    
	outs, errs = proc.communicate(input=input_binary_string, timeout=15)
	proc.stdin.close()
	return outs.decode('UTF-8')

def generate_tons_of_points(number):

	generated_string=""
	for i in range(number):
		generated_string+= str(randint(*RANGE)) +"," + str(randint(*RANGE))+"\n"
	return generated_string



def run_single_test(test_input):
	print("running test...")

	ret = open_program_with_input(MY_PROGRAM_NAME,test_input.encode('utf-8'))
	student_results=ret.split("result\n")[1:]
	# print(student_results)
	ret = open_program_with_input(SKOOL_PROGRAM_NAME,test_input.encode('utf-8'))
	skool_results=ret.split("result\n")[1:]
	# print(skool_results)
	flag=True

	if len(student_results)==0 and skool_results!=['']:
		print("---\nerror in comparison, test was:\n"+test_input+"\nyou: "+str(student_results)+"\nskool: "+str(skool_results)+"\n")
		flag=False
	else:
		for x in student_results:
			if VERY_VERBOSE: 
				print("---\nnow comparing: \n"+x+"\n"+skool_results[0]+"----\n")
			if x!=skool_results[0]:
				print("---\nerror in comparison, test was:\n"+test_input+"\nyou: "+x+"\nskool: "+skool_results[0]+"\n")
				flag=False
				break
	print(flag)
	print("===============================================================")


def run_test_suite(iters):
	for i in range(iters):
		gen_input=generate_tons_of_points(0+i)
		run_single_test(gen_input)

run_single_test(BASIC_TEST_INPUT)
run_single_test(HARD_CASE_1)
run_single_test(HARD_CASE_2)
run_single_test(HARD_CASE_3)
run_test_suite(500)
