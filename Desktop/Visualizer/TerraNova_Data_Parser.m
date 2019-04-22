function T = TerraNova_Data_Parser(filename)

data = [];
names = {};
series = {};

fid = fopen(filename);

while ~feof(fid)
    line = fgets(fid);
    strs = split(line, ',');
    
    if strcmp(strs{1}, 'DATADEF')
        names(str2double(strs{2}) + 1) = cellstr(strs{3});
        series{str2double(strs{2}) + 1} = timeseries([],[]);
    elseif strcmp(strs{1},'DATA')
        series{str2double(strs{3}) + 1} = addsample(series{str2double(strs{3}) + 1}, 'Data', str2double(strs{4}), 'Time', str2double(strs{2})); 
    end
end

Name = names';
Data = series';

T = table(Name, Data);

end