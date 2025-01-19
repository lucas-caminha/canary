local effects = {
    {position = Position(32373, 32233, 7), text = 'Free Blessings!', effect = CONST_ME_HOLYAREA},
    {position = Position(32380, 32240, 7), text = 'Tigrinho $$', effect = CONST_ME_FIREATTACK},
    {position = Position(32373, 32236, 7), text = 'Recompensa Diaria', effect = CONST_ME_HEARTS},
}

local animatedText = GlobalEvent("AnimatedText") 
function animatedText.onThink(interval)
    for i = 1, #effects do
        local settings = effects[i]
        local spectators = Game.getSpectators(settings.position, false, true, 7, 7, 5, 5)
        if #spectators > 0 then
            if settings.text then
                for i = 1, #spectators do
                    spectators[i]:say(settings.text, TALKTYPE_MONSTER_SAY, false, spectators[i], settings.position)
                end
            end
            if settings.effect then
                settings.position:sendMagicEffect(settings.effect)
            end
        end
    end
   return true
end

animatedText:interval(4550)
animatedText:register()