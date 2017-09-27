import codecs
import shutil


def replace(headers):
    for header in headers:
        shutil.copy(header, header.replace(".h",".bak"))
        f = codecs.open(header, 'r', encoding='utf8')
        read_file = f.read()
        f.close()
        new_file = codecs.open(header,'w', encoding='utf8')
        for line in read_file.split("\n"):
            new_file.write(line.replace('private', 'public'))
        new_file.close()


replace(["1234.h"])