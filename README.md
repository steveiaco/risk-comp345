# risk-comp345
COMP345 Semester project

Please do not modify the master branch directly.

When you want to add your part to the project, create a sub-branch to the test branch with your part. 
To do so, do:

git checkout -b <name_new_branch> <parent_branch>

Test the merging of the code in the test branch to make sure everything is fine. 

The test branch will serve as a master branch. This is where you will be able to test the parts of everyone being put together.

If the test branch is working fine and has been tested, then it can be merged with the master branch.

Warning: (These commands below will affect your local project files)

To do the merge, do:

git checkout <branch you want to merge to>

git merge <branch you want to merge with>

(Then add the changes to the remote repo)

git add .

git commit -m "Merge with _branch_name_"

git push
