local ferumbrasAscendantMysterious = Action()
function ferumbrasAscendantMysterious.onUse(player, item, fromPosition, target, toPosition, isHotkey)
		local useItem = config[item.itemid]
		if player:hasMount(87) then
			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "You already have this mount.")
			return false
		end

		player:addMount(87)
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "You decipher something! You get a rift runner to accompany you on your journey.")
		player:setStorageValue(Storage.Quest.U10_90.FerumbrasAscension.RiftRunner, 1)
		item:remove(1)
	return true
end

ferumbrasAscendantMysterious:id(22865)
ferumbrasAscendantMysterious:register()
