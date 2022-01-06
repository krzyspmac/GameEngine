function init()
	scene:SetMouseDownFunction("mouseDown")
end

function mouseDown(x, y)
	print ("mouse down at " .. x .. ", " .. y)
end
