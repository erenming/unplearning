#!/usr/bin/env python
# coding=utf-8
import sys
import os
import subprocess


def run_cmd(cmd, cwd):
    p = subprocess.Popen(cmd, cwd=cwd, shell=True, stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE)
    while True:
        line = p.stdout.readline()
        if line != '':
            # the real code does filtering here
            print(line.rstrip())
        else:
            break
    p.wait()
    if p.returncode != 0:
        raise RuntimeError(p.stderr.read())

if __name__ == "__main__":
    fpath = sys.argv[1]
    filename = fpath.split("/")[-1].split(".")[0]
    run_cmd("gcc {} -o bin/{} -lunp".format(fpath, filename), cwd=os.getcwd())