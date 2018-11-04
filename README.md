Multiplatform/Multicompiler Travis CI Example
=============================================

This repository contains a simple, minimal set of files for demonstrating how to
configure Travis CI to build and execute a single C binary on multiple platforms
and using multiple compilers on each platform.  The contents of the C file
require linking against lapack, which is not necessarily available by default in
the build environment of each platform.  Therefore, the Travis CI file also shows how to install
dependencies manually.

After creating this repository, it was connected to Travis CI for automatic execution on pushes and pull requests.  This is done by
1. creating an account in Travis CI if necessary and authorizing Travis CI to connect to my GitHub account and
2. activating this repository in the Travis CI account's Settings page (you may need to first sync Travis CI with GitHub through the Settings page).

The file `.travis.yml` is the configuration file that tells Travis CI what it
needs to do with each job.  In this example, it configures Travis CI to run
four different builds in parallel - two with Linux and two with OS X.  For each
OS, Travis CI uses specific versions of gcc and clang.  If these versions are
not included in the default build environments, then they are installed using
the Travis CI addon package manager for each OS. 

The program `solve_problem.c` solves a single simple linear system using a
lapack routine and confirms that the result is correct within a specific
tolerance.  Note that if the solution is too poor, then the program returns a 
non-zero exit code, which Travis CI will interpret as failure.  Commits or pull 
requests that end with non-zero exit codes should therefore be marked as 
failures in GitHub.  If the program terminates successfully, then this script
returns an exit code of zero, which Travis CI indicates as success.  Green
checkmarks should be shown in GitHub to reflect this success.

To see the Travis CI build history and logs, navigate to the [Travis CI page](https://travis-ci.org/jrdoneal/CI_Multiplatform) 
linked to this repository.  Also, you can jump to the Travis CI build log for a build triggered
by a particular commit by clicking on the green checkmark or red X associated
with the commit in the [GitHub commit history](https://github.com/jrdoneal/CI_Multiplatform/commits/master) 
of this repository.

