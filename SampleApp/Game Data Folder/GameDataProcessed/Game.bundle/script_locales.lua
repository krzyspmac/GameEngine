local i18n = { locales = {} }

local currentLocale = 'en' -- the default language

function i18n.setLocale(newLocale)
  currentLocale = newLocale
  assert(i18n.locales[currentLocale], ("The locale %q was unknown"):format(newLocale))
end

local function translate(id)
  local result = i18n.locales[currentLocale][id]
  assert(result, ("The id %q was not found in the current locale (%q)"):format(id, currentLocale))
  return result
end

i18n.translate = translate

setmetatable(i18n, {__call = function(_,...) return translate(id) end})

return i18n
