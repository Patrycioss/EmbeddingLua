function GetPalindromesUntil(max)
    local palindromes = {}
    local i = 1
    while i < max do
        if IsPalindrome(i) then
            table.insert(palindromes, i)
        end
        i = i + 1
    end
    return palindromes
end

function IsPalindrome(input)  
    local inputString = tostring(input)
    local reverse = string.reverse(inputString)
    return inputString == reverse
end