### Default .bashrc Setup
### By J. Farran

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

. /data/shell-syswide-setup/system-wide-bashrc

### Software modules to automatically load.  Cluster_Defaults provides a
### basic set of software.  Comment it out if you don't want any and wish to
### load your own.  Add more below to select your own specific software to
### load each time you login.   Type 'module available' to see entire list.

module load Cluster_Defaults
