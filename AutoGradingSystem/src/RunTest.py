import subprocess
from os import chdir, getcwd
from os.path import  join, basename, exists, abspath


'''
빌드 테스트를 위한 모듈
학생의 main 소스를 이용하여 컴파일 및 빌드
stderr를 redirection하여 log(Make_RunTest.log)로 남긴다.
#CompileTest 생성 시 True, 없을 시 False 반환
'''
result_dir = '../../result'


def RunTest(student_dir):
    RunFlag = ExecTest(student_dir)
    return RunFlag

def ExecTest(student_path):
    origin_path = getcwd();
    chdir(student_path)
    student_result_dir = join(result_dir, basename(student_path))
    student_result_dir = abspath(student_result_dir)

    subprocess.call('make compile 2>' + student_result_dir + '/Make_RunTest.log;', shell=True)

    if exists('CompileTest'):
        chdir(origin_path)
        return True
    else:
        chdir(origin_path)
        return False
