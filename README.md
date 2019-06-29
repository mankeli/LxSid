# LXSid

Random SID player plugin for LXDE LXPanel! Uses HVSC and resid-fp.

## installation
Just say "make install" in the source directory. This will compile the plugin, copies it and the scripts to correct places, generates HVSC sid list cache, and restarts lxpanel.

Note: This assumes your HVSC library is at path ~/C64Music/ ! If not, some hard-coded paths should be replaced.

## usage
Just add LXSid to your panel. Click it to start random SID song playback, click it again to stop.


## future
There's also "rating system", which gets installed to ~/C64Music/lxsid/lxsid_rate.sh .

Rating script takes parameters "quality" and "sadness", which get logged into ~/C64Music/lxsid/sidratings.log. Ratings are not used anywhere currently.
