#!/bin/bash

path="src/account_management.c"

git add "$path"
git commit -m "Changed by Piyush"

git pull piyush main --rebase

git push piyush main
git push ayush main
