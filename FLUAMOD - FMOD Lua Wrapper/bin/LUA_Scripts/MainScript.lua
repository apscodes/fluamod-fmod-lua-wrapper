function Start()
	L_PlaySound()	
end

function L_PlaySound()
	--PlaySound()
	--PlaySound("background_music.ogg")
	PlaySound("background_music.ogg", (1000))--max 44100
	PlaySound("background_music.ogg", (32500))--max 44100
end

function Destroy() 
end 

function Update(dt) 
end 
	
function Draw() 
end