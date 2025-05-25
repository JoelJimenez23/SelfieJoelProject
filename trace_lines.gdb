set pagination off
set logging on
set logging file trace.log
set logging overwrite on
break mipster
break handle_exception
break handle_system_call
break implement_request_bankers
run
while 1
  info line
  next
end

