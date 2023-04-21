
Player = {number = 0}

function Player:new(i)
    local self = setmetatable({}, Player)
    self.number = i
    return self
end

function SpawnPlayers(n)
    local players = {}
    for i = 1, n do
        newPlayer = Player:new(i*5)
        players [i] = newPlayer
    end
    return players
end

