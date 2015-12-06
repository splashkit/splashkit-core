# Generates a code snippet from a provided gist_id and filename
def code_snippet(gist_id, filename)
  types = {
    'Psuedocode' => 'psuedocode',
    'C/C++'      => 'c',
    'Pascal'     => 'pas',
    'Swift'      => 'swift',
    'Python'     => 'py'
  }

  default_type = 'psuedocode'

  # Auto Generation of HTML
  list_items = ""
  tab_panes = ""
  types.each do |pretty_type, type|
    tab_id = "#{gist_id}-#{type}"
    gist_file = "#{filename}.#{type}"

    # Generate the <li> items HTML
    list_items << "<li role='presentation'"
    list_items <<  (type == default_type ? "class='active'" : "")
    list_items << "><a href='##{tab_id}' aria-controls='#{tab_id}' role='tab' data-toggle='tab'>#{pretty_type}</a></li>"

    # Generate the tab panes HTML
    tab_panes << "<div role='tabpanel' id='#{tab_id}' class='tab-pane"
    tab_panes << (type == default_type ? " active'>" : "'>")
    tab_panes << "<script data-gist src='https://gist.github.com/#{gist_id}.js?file=#{gist_file}' type='text/javascript'></script>"

    tab_panes << "</div>"
  end

  # This is where we generate our HTML
  return <<-EOS
    <!-- Code snippet #{filename} (#{gist_id}) -->
    <div class="code-snippet">
    <ul class='nav nav-tabs' role='tablist'>
    #{list_items}
    </ul>
    <div class='tab-content'>
    #{tab_panes}
    </div>
    </div>
    <!-- End code snippet -->
  EOS
end