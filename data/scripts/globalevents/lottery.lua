local lottery = GlobalEvent("lottery")

local config = {
    interval = 60, -- 1 minute
    rewards = {
	{22722, 1}, 	
    }
}

function lottery.onThink(interval)
    local players = {}
    for _, player in ipairs(Game.getPlayers()) do
        if not player:getGroup():getAccess() then
            table.insert(players, player)
        end
    end

    local c = #players
    if c <= 0 then
        return true
    end

    local winner = players[math.random(#players)]

    local reward = config.rewards[math.random(#config.rewards)]
    local itemid, amount = reward[1], reward[2]
    winner:addItem(itemid, amount)

    local it = ItemType(itemid)
    local name = (amount == 1) and (it:getArticle() .. " " .. it:getName()) or (amount .. " " .. it:getPluralName())

    broadcastMessage("[LOTTERY SYSTEM] " .. winner:getName() .. " recebeu " .. name .. "! Parabens! (Proxima loteria em " .. config.interval .. " minutos)")

    return true
end

lottery:interval(config.interval * 60 * 1000) -- Convert minutes to milliseconds
lottery:register()