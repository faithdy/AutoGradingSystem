import subprocess
from os import chdir, getcwd, mkdir, chmod
from os.path import  join, basename, exists, abspath

result_dir = '../../result'


def RunTest(student_dir):
    RunFlag = ExecTest(student_dir)
    return RunFlag

def ExecTest(student_path):
    origin_path = getcwd();
    chdir(student_path)
    student_result_dir = join(result_dir, basename(student_path))
    student_result_dir = abspath(student_result_dir)

    subprocess.call('make compile>>' + student_result_dir + '/Make_RunTest.log;', shell=True)

    if exists('CompileTest'):
        chdir(origin_path)
        return True
    else:
        chdir(origin_path)
        return False
