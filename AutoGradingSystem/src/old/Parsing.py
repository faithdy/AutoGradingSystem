from xml.etree.ElementTree import parse
from os.path import join, basename, splitext, abspath



def parsing(student_dir,xml):
    student_dir = abspath(student_dir)
    tree = parse(student_dir,"/Result/Death_test.xml")
    root = tree.getroot()
    arr = []

    for test in root.iter("testcase") :
        if test.find("failure") is None :
            arr.append(test.attrib["name"])

    return arr

