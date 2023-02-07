#idf_component_register(SRCS "main.c"
#                    INCLUDE_DIRS ".")

set(app_sources
	"main.c"
	"peripSDR.c"
	"selectTask.c"
	"MQTT_Worker.c"
)

idf_component_register(SRCS ${app_sources}
		INCLUDE_DIRS "." "../include"
		REQUIRES )