lxsid.so: lxsid.c
	gcc -Wall `pkg-config --cflags gtk+-2.0 lxpanel` -shared -fPIC $< -o $@ `pkg-config --libs lxpanel`

# hack to make sidlist
sidlist.txt:
	find ~/C64Music/ -name *sid > sidlist.txt

C64MUSIC_LXSID=~/C64Music/lxsid/

install: lxsid.so lxsid_play.sh lxsid_rate.sh sidlist.txt
	echo $(C64MUSIC_LXSID)
	mkdir -p $(C64MUSIC_LXSID)
	cp lxsid_play.sh $(C64MUSIC_LXSID)
	cp lxsid_rate.sh $(C64MUSIC_LXSID)
	cp sidlist.txt $(C64MUSIC_LXSID)
	sudo cp lxsid.so /usr/lib/x86_64-linux-gnu/lxpanel/plugins
	lxpanelctl restart
