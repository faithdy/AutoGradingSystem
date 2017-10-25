'''
function_name = 과제 이름
test_fixture = 테스트 시 선택할 fixture(Set Up)
function_count = 시나리오 내 Call 하는 함수 갯수
death_index = 데스 테스트 실행 시 선택할 함수
functions = 시나리오 함수 리스트
'''
class Scenario:
    function_name = ''
    test_fixture = ''
    function_count = 0
    death_index = []
    functions = []

    def __init__(self, name):
        self.function_name = name
        self.functions = []

    def SetScenario(self, cfg):
        self.function_count = int(cfg.get(self.function_name, 'function_count'))
        self.test_fixture = cfg.get(self.function_name, 'test_fixture')

        death_index = cfg.get(self.function_name, 'death_index')
        self.death_index = death_index.split(' ')

        for i in range(self.function_count):
            self.functions.append(cfg.get(self.function_name, 'function_'+str(i)))