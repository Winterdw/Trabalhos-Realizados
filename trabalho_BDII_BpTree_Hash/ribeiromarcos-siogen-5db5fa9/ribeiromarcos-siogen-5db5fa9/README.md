# SIOgen
Simple Insert Delete Dataset Generator


SIOgen
===

**Table of Contents**

- [Introduction](#introduction)
- [Command Line Usage](#command-line-usage)

# Introduction

SIOgen is just a simple tool to genarate synthetic datasets.
The datasets are composed by insertions and deletions of records.
The records are collections of integer attributes.  
The attribute A1 is a key attribute having a unique value
for each record. 

# Command Line Usage

The command line parameters are:
- -a/--attributes: Number of attributes
- -i/--insertions: Number of insertions
- -d/--deletions: Number of deletions
- -f/--filename: Output filename
