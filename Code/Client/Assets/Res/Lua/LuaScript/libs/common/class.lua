
function inherit_from(base, init)
    local c = {} -- a new class instance
    if not init and "function" == type(base) then
        init = base
        base = nil
    elseif "table" == type(base) then
        -- our new class is a shallow copy of the base class!
        for i, val in pairs(base) do
            c[i] = val
        end
        c._base = base
    end
    c.__index = c
    c.init = init
    c.is = function(self, class_type)
        local m = getmetatable(self)
        while m do
            if m == class_type then
                return true
            end
            m = m._base
        end
        return false
    end
    c.new = function(self, ...)
        return self(...)
    end
    local mt = {}
    -- expose a constructor which can be called by <classname>(<args>)
    mt.__call = function(class_tbl, ...)
        local o = {}
        setmetatable(o, c)
        if class_tbl.init then
            class_tbl.init(o, ...)
        else
            -- make sure that any stuff from the base class is initialized!
            if base and base.init then
                base.init(o, ...)
            end
        end
        return o
    end
    setmetatable(c, mt)
    return c
end