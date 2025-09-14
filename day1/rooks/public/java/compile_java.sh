#!/bin/bash

TASK=rooks

javac ${TASK}.java grader.java
jar cf ${TASK}.jar *.class