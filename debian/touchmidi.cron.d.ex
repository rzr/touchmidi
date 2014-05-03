#
# Regular cron jobs for the touchmidi package
#
0 4	* * *	root	[ -x /usr/bin/touchmidi_maintenance ] && /usr/bin/touchmidi_maintenance
