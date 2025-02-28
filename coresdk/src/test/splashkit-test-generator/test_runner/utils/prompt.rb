# Prompts user for confirmation before running interactive tests
class Prompt
  def self.confirm_manual_test(group)
    print "\nWarning: '#{group}' requires manual interaction. Continue (y), skip (n)? (y/n): "
    confirmed = gets.chomp.downcase == 'y'
    puts "\nSkipping '#{group}'" unless confirmed
    confirmed
  end
end
