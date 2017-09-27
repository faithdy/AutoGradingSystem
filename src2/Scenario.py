
class Scenario:
    function_name = ''
    function_count = 0
    death_index = []
    functions = []

    def __init__(self, name):
        self.function_name = name

    def SetScenario(self, cfg):
        self.function_count = int(cfg.get(self.function_name, 'function_count'))

        death_index = cfg.get(self.function_name, 'death_index')
        self.death_index = death_index.split(' ')

        for i in range(self.function_count):
            self.functions.append(cfg.get(self.function_name, 'function_'+str(i)))