function AppendItemAlias(item, aliases)
	for i = 1, #aliases do
		item:AddAlias(aliases[i])
	end
end
function AppendPromptResponses(responses)
	for i = 1, #responses do
		Manager:AddPromptResponse(responses[i])
	end
end
function Contains(list, test_value)
	for key,value in ipairs(list) do
		if value == test_value then
			return true
		end
	end
	return false
end