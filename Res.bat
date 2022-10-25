
resources = %~1
target_resources = %~2
IF exist target_resources rd target_resources
MKDIR  target_resources
XCOPY resources target_resources /e /h /y