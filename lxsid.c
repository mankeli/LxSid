#include <lxpanel/plugin.h>

#include <stdio.h>

// internal to the plugin source, not used by the 'priv' variable
static int iInstanceCount = 0;

/* the plugin's id – an instance of this struct 
	 is what will be assigned to 'priv' */
typedef struct 
{
	gint iMyId;
	GtkWidget *box;
	GtkWidget *pLabel;
	GPid sidplayerpid;
} TestPlugin; 

static gboolean _label_update(gpointer data)
{
	GtkLabel *label = (GtkLabel*)data;
	gtk_label_set_label(label, "LXSid");
	return FALSE;
}

static gboolean on_button_press( GtkWidget* widget, GdkEventButton* evt, LXPanel *panel )
{
	TestPlugin *pTest = lxpanel_plugin_get_data(widget);


	if (pTest->sidplayerpid)
	{
		printf("killing %i\n", pTest->sidplayerpid);
		kill(pTest->sidplayerpid, SIGTERM);
		g_spawn_close_pid(pTest->sidplayerpid);
		pTest->sidplayerpid = 0;

		char labelbuf[10] = {'\0'};
		snprintf(labelbuf, sizeof(labelbuf), "STAP!");
		gtk_label_set_text((GtkLabel *)pTest->pLabel, labelbuf);
		gtk_widget_set_tooltip_text(pTest->box, "");
	}
	else
	{
		gchar *spargv[] = {"./C64Music/lxsid/lxsid_play.sh", NULL};
		GError *error = NULL;
		g_spawn_async (NULL, spargv, NULL, G_SPAWN_DEFAULT, NULL, NULL, &(pTest->sidplayerpid), &error);
		if( error != NULL )
		{
			printf("error: %s\n", error->message);
			g_clear_error (&error);
		}

		gtk_label_set_text((GtkLabel *)pTest->pLabel, "PLAY!");

		char labelbuf[10] = {'\0'};
		snprintf(labelbuf, sizeof(labelbuf), "p %i", pTest->sidplayerpid);

		gtk_widget_set_tooltip_text(pTest->box,labelbuf);

	}

	g_timeout_add(500, _label_update, pTest->pLabel);

	return TRUE;
}

GtkWidget *lxsid_constructor(LXPanel *panel, config_setting_t *settings)
{
 /* panel is a pointer to the panel and
		 settings is a pointer to the configuration data
		 since we don't use it, we'll make sure it doesn't
		 give us an error at compilation time */
	(void)panel;
	(void)settings;

 // allocate our private structure instance
	TestPlugin *pTest = g_new0(TestPlugin, 1);

 // update the instance count
	pTest->iMyId = ++iInstanceCount;

 // make a label out of the ID
	char cIdBuf[10] = {'\0'};

	snprintf(cIdBuf, sizeof(cIdBuf), "LXSid%d", pTest->iMyId);

 // create a label widget instance 
	pTest->pLabel = gtk_label_new(cIdBuf);

 // set the label to be visible
	gtk_widget_show(pTest->pLabel);

 // need to create a container to be able to set a border
	GtkWidget *p = gtk_event_box_new();

	pTest->box = p;

 // our widget doesn't have a window...
 // it is usually illegal to call gtk_widget_set_has_window() from application but for GtkEventBox it doesn't hurt
	gtk_widget_set_has_window(p, FALSE);

 // bind private structure to the widget assuming it should be freed using g_free()
	lxpanel_plugin_set_data(p, pTest, g_free);

 // set border width
	gtk_container_set_border_width(GTK_CONTAINER(p), 1);

 // add the label to the container
	gtk_container_add(GTK_CONTAINER(p), pTest->pLabel);
	pTest->sidplayerpid = 0;

 // set the size we want
	gtk_widget_set_size_request(p, 60, 25);

	g_timeout_add(500, _label_update, pTest->pLabel);

 // success!!!
	return p;
}

FM_DEFINE_MODULE(lxpanel_gtk, lxsid)

/* Plugin descriptor. */
LXPanelPluginInit fm_module_init_lxpanel_gtk = {
	.name = "LXSid",
	.description = "Random SID player",

	 // assigning our functions to provided pointers.
	.new_instance = lxsid_constructor,
	.button_press_event = on_button_press
};
