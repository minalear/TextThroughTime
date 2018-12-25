function AppendItemAlias(item, aliases)
	for i = 1, #aliases do
		item:AddAlias(aliases[i])
	end
end
function Contains(list, test)
	return list[test] ~= nil
end